const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.resolveTargetQuery(.{
        .cpu_arch = .thumb,
        .os_tag = .freestanding,
        .abi = .eabi,
        .cpu_model = .{
            .explicit = &std.Target.arm.cpu.cortex_m0plus,
        },
    });
    const optimize = b.standardOptimizeOption(.{});

    // base app
    const app = b.addModule("app", .{
        .target = target,
        .optimize = optimize,
        .root_source_file = b.path("src/main.zig"),
    });
    app.addCSourceFiles(.{ .files = &.{ "startup/cortex-m.c", "src/system_py32f0xx.c" } });

    const exe = b.addExecutable(.{
        .name = "demo",
        .root_module = app,
    });

    exe.addObjectFile(b.path("build/libhal.a"));
    exe.addIncludePath(b.path("picolibc/newlib/libc/include"));
    exe.addIncludePath(b.path("picolibc/newlib/libc/tinystdio"));
    exe.addIncludePath(b.path("inc"));
    exe.addIncludePath(b.path("PY32F0xx_Firmware/Drivers/PY32F0xx_HAL_Driver/Inc"));

    // add reg header file
    exe.addIncludePath(b.path("PY32F0xx_Firmware/Drivers/CMSIS/Include"));
    exe.addIncludePath(b.path("PY32F0xx_Firmware/Drivers/CMSIS/Device/PY32F0xx/Include"));

    exe.setLinkerScript(b.path("startup/standalone.ld"));

    b.installArtifact(exe);
}
