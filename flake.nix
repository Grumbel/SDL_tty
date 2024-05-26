{
  description = "Terminal-like text output for SDL";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs?ref=nixos-24.05";
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
         packages = rec {
           default = SDL_tty;

           SDL_tty = pkgs.stdenv.mkDerivation {
             name = "SDL_tty";

             src = nixpkgs.lib.cleanSource ./.;

             nativeBuildInputs = with pkgs; [
               cmake
               pkg-config
             ];

             buildInputs = with pkgs; [
               SDL
               SDL_image
             ] ++ [
               tinycmmc.packages.${system}.default
             ];
           };
        };
       }
    );
}
