{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = with pkgs.buildPackages; [ gnumake bear clang-tools gdb valgrind llvmPackages.openmp ];
}

