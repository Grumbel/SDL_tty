{
  description = "Terminal-like text output for SDL";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-21.11";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
       in rec {
         packages = flake-utils.lib.flattenTree rec {
           SDL_tty = pkgs.stdenv.mkDerivation {
             name = "SDL_tty";
             src = nixpkgs.lib.cleanSource ./.;
             cmakeFlags = [];
             nativeBuildInputs = [
               pkgs.cmake
               pkgs.pkgconfig
             ];
             buildInputs = [
               pkgs.SDL
               pkgs.SDL_image
             ];
           };
        };
        defaultPackage = packages.SDL_tty;
      });
}
