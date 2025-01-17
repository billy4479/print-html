{
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    { self
    , nixpkgs
    , flake-utils
    }:
    flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.default = pkgs.mkShell {
        packages = with pkgs; [
          zls
          clang-tools
        ];
        buildInputs = with pkgs; [
          qt6.qtbase
          qt6.qtwebengine
        ];
        nativeBuildInputs = with pkgs; [
          zig
          cmake
          ninja
        ];
      };
    });
}
