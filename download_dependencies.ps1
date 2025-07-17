# Copyright Kyungkun Ko


param ($upgrade)


$deps = "vcpkg-pkgconfig-get-modules",
        "zlib",
		"zstd",
		"liblzma",
		"openssl",
		"tinyxml2",
		"libxml2[iconv]",
		"libbson",
		"jsoncpp",
		"avro-c",
		"protobuf",
		"grpc",
		"pthread",
		"pthreads",
		"libuv",
		"libevent",
		"lcms",
		"tiff",
		"libpng",
		"icu",
		"freetype",
		"libiconv",
		"jasper",
		"openexr",
		"jansson",
		"libjpeg-turbo",
		#"openal-soft",
		"libbson",
		"libsndfile",
        "libogg",
        "libflac",
		"opus",
		"libwebsockets",
		"curl[openssl,websockets]",
		"librdkafka[zlib]",
		"mysql-connector-cpp",
		"gtest",
		"recastnavigation",
		"vulkan",
		"protobuf",
		"openssl",
		"grpc"



# Doesn't compile nicely on windows		
#not supported by VCPKG
		#"pipewire"
	   #"yaml",
	   #"libmng",


$sharedlib_deps = "msquic[0-rtt]"



$ErrorActionPreference = 'Stop'


$prevDir=pwd

try {
	
	$vcpkgdir = "../vcpkgWin"
	$gittag = "2025.06.13"
	$triplet = "x64-windows-static"
	$triplet_shared = "x64-windows"
	
	Write-Host "Checking for $vcpkgdir..., triplet:$triplet"
	
	Write-Host "Checking for $vcpkgdir..."
	
	if (-not (Test-Path $vcpkgdir)) {
		git clone --branch $gittag --single-branch https://github.com/Microsoft/vcpkg.git $vcpkgdir
	}

	cd $vcpkgdir

	if (-not (Test-Path -LiteralPath vcpkg.exe)) {
		Write-Host "Installing vcpkg..."
		./bootstrap-vcpkg.bat -disableMetrics
	}

	Write-Host "Beginning package install..."

	./vcpkg.exe install $deps --triplet $triplet --allow-unsupported
	
	./vcpkg.exe install $sharedlib_deps --triplet $triplet_shared 
	
	if ($upgrade = 1)
	{
		Write-Host "Upgrading ($upgrade)..."
		git pull 
		./vcpkg.exe update
		./vcpkg.exe upgrade --no-dry-run --allow-unsupported
	}
	else
	{
		Write-Host "Skip upgrade ($upgrade)..."
		Write-Host "	specify parameter to upgrade example:"download_dependencies.ps1 -upgrade 1""
	}
	
	cd ..\StormForge\3rdParties
	
	.\WinGenNBuild.cmd

} catch {
	# rethrow
	throw $_
} finally {
	# restore previous directory
	cd $prevDir
}
