# SPDX-FileCopyrightText: 2022 Noah Fontes
#
# SPDX-License-Identifier: Apache-2.0

{
  outputs = { self, nixpkgs }: with nixpkgs.lib; let
    allSystems = builtins.map (system: let
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.${system}.default = with pkgs; mkShell {
        nativeBuildInputs = [
          meson
          ninja
        ];
      };

      packages.${system} = rec {
        choysh = with pkgs; stdenv.mkDerivation {
          pname = "choysh";
          version = "1.0.2";

          src = ./.;

          nativeBuildInputs = [
            meson
            ninja
          ];

          meta = {
            description = "User's choice of shell";
            homepage = "https://github.com/impl/choysh";
            license = pkgs.lib.licenses.asl20;
          };

          passthru = {
            shellPath = "/bin/choysh";
          };
        };
        default = choysh;
      };
    }) systems.flakeExposed;
  in builtins.foldl' recursiveUpdate {} allSystems;
}
