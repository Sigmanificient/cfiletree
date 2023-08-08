{
  description = "CFileTree";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system: let
      pkgs = nixpkgs.legacyPackages.${system};
      cc = pkgs.gcc12;

      name = "cfiletree";
      libs = with pkgs; [ csfml ];

      mkInstall = bin: ''
        mkdir -p $out/bin
        cp ${bin} $out/bin
      '';
    in rec {
      devShells.default = pkgs.mkShell {
        packages = with pkgs; [
          glibc
          gcovr
          ltrace
          gnumake
          valgrind
        ] ++ [ cc ] ++ libs;
      };

      packages = {
        ${name} = pkgs.stdenv.mkDerivation {
          inherit name;

          src = ./.;
          makeFlags = [ "CC=${cc}/bin/gcc" ];

          # ↓ Makefile tput
          buildInputs = libs ++ [ pkgs.ncurses ];

          hardeningDisable = [ "format" "fortify" ];
          installPhase = mkInstall name;
        };

        debug = packages.${name}.overrideAttrs({
          name = "debug";

          installPhase = mkInstall "debug";
          buildPhase = ''
            make debug
          '';
        });

        default = self.packages.${system}.${name};
      };
    });
}
