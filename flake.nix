{
  description = "A comprehensive C development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            gcc
            gnumake
            cmake
            pkg-config
            gdb
            valgrind
            clang-tools
          ];

          shellHook = ''
            echo "--- C Development Environment Loaded ---"
            echo "Compiler: $(gcc --version | head -n 1)"
            echo "Build tools: make, cmake, pkg-config"
          '';
        };

        pkgs.default = pkgs.stdenv.mkDerivation {
          pname = "chip-8-emulator";
          version = "0.1";
          src = ./src;
          nativeBuildInputs = [ pkgs.cmake pkgs.gcc ];
        };
      });
}
