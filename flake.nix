{
  description = "Terminal-like text output for SDL";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";

    tinycmmc.url = "github:grumbel/tinycmmc";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";
    tinycmmc.inputs.flake-utils.follows = "flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, tinycmmc }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
       in {
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
               tinycmmc.packages.${system}.default

               pkgs.SDL
               pkgs.SDL_image
             ];
           };
           default = SDL_tty;
        };
       }
    );
}
