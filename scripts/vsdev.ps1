# justfile のレシピから dot-source して使う開発環境セットアップ。
#   - MSVC 開発者環境 (cl / Windows SDK) に未突入なら Launch-VsDevShell.ps1 で入る
#   - VCPKG_ROOT が実在しないパスなら、ユーザー/マシン環境変数の値で補う

$ErrorActionPreference = 'Stop'
# MSVC のメッセージを英語に固定する
# 　- Ninja が /showIncludes の出力（ヘッダの依存関係）を確実に読み取れるようにする
# 　- エラーメッセージをそのまま検索しやすくする
$env:VSLANG = '1033'

# --- VCPKG_ROOT -------------------------------------------------------------
if (-not $env:VCPKG_ROOT -or -not (Test-Path $env:VCPKG_ROOT)) {
    $candidates = @(
        [Environment]::GetEnvironmentVariable('VCPKG_ROOT', 'User'),
        [Environment]::GetEnvironmentVariable('VCPKG_ROOT', 'Machine')
    ) | Where-Object { $_ -and (Test-Path $_) }

    if ($candidates) {
        $env:VCPKG_ROOT = @($candidates)[0]
    } else {
        throw "VCPKG_ROOT が見つかりません (現在値: '$env:VCPKG_ROOT')。環境変数を設定してください。"
    }
}

# --- MSVC 開発者環境 --------------------------------------------------------
if (-not (Get-Command cl.exe -ErrorAction SilentlyContinue)) {
    $installerDir = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer'
    $vswhere = Join-Path $installerDir 'vswhere.exe'
    if (-not (Test-Path $vswhere)) {
        throw "vswhere.exe が見つかりません: $vswhere"
    }

    $vsPath = & $vswhere -latest -products * `
        -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
        -property installationPath
    if (-not $vsPath) {
        throw 'C++ ツールセット付きの Visual Studio が見つかりません。'
    }

    # Launch-VsDevShell.ps1 は内部で vswhere を PATH から呼ぶため先に通しておく
    $env:PATH = "$installerDir;$env:PATH"

    & (Join-Path $vsPath 'Common7\Tools\Launch-VsDevShell.ps1') `
        -Arch amd64 -HostArch amd64 -SkipAutomaticLocation | Out-Null
}

$ErrorActionPreference = 'Continue'
