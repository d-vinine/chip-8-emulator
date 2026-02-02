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

          # Libraries your project links against
          buildInputs = with pkgs; [
            # Add libraries here (e.g., check, openssl, zlib)
          ];

          shellHook = ''
            echo "--- C Development Environment Loaded ---"
            echo "Compiler: $(gcc --version | head -n 1)"
            echo "Build tools: make, cmake, pkg-config"
          '';
        };
      });
}
