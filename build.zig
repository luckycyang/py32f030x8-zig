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

    const app = b.addModule("app", .{
        .target = target,
        .optimize = optimize,
    });

    app.addCSourceFiles(.{ .files = &.{ "src/main.c", "startup/cortex-m.c" } });

    const exe = b.addExecutable(.{
        .name = "demo",
        .root_module = app,
    });

    exe.setLinkerScript(b.path("startup/standalone.ld"));

    b.installArtifact(exe);
}
