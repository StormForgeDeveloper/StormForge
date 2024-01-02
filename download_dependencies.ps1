# Copyright Kyungkun Ko


$deps = "vcpkg-pkgconfig-get-modules",
        "zlib",
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
		"openal-soft",
		"sndfile",
        "libogg",
        "libflac",
		"opus",
		"libwebsockets",
		"curl[openssl,websockets]",
		"librdkafka[zlib]",
		"mysql-connector-cpp",
		"gtest",
		"recastnavigation",
		"vulkan"

#Those are complicated and being separated shared lib is better
$deps_shared =
	"libbson",
	"protobuf",
	"grpc",
	"openssl",
	"mongo-c-driver[icu]",
	"zookeeper"


# Doesn't compile nicely on windows		
#not supported by VCPKG
		#"pipewire"
	   #"yaml",
	   #"libmng",

$ErrorActionPreference = 'Stop'

function vcpkg_install {
	Param(
		[string[]] $packages,

		[string] $targetTriplet
	)
	
	./vcpkg.exe install $packages --triplet $targetTriplet  --recurse

	if (-not $?) {
		Write-Error("Failed at installing package $package ($targetTriplet)")
	}
}

$prevDir=pwd

try {
	
	$vcpkgdir = "./vcpkg"
	$triplet = "x64-windows-static"
	$triplet_shared = "x64-windows"
	
	Write-Host "Checking for $vcpkgdir..., triplet:$triplet"
	
	Write-Host "Checking for $vcpkgdir..."
	if (-not (Test-Path $vcpkgdir)) {
		git clone https://github.com/Microsoft/vcpkg.git
		
		cd $vcpkgdir
	}
	else {
		cd $vcpkgdir
		git pull 
	}


	if (-not (Test-Path -LiteralPath vcpkg.exe)) {
		Write-Host "Installing vcpkg..."
		./bootstrap-vcpkg.bat -disableMetrics
	}

	Write-Host "Beginning package install..."

	# protobuf uses x64-windows tool even though it has one for target triplet
	./vcpkg.exe install $deps_shared --triplet $triplet_shared

	./vcpkg.exe install $deps --triplet $triplet
	
	./vcpkg.exe update
	./vcpkg.exe upgrade --no-dry-run --allow-unsupported
	
	cd ..\3rdParties
	
	.\WinGenNBuild.cmd

} catch {
	# rethrow
	throw $_
} finally {
	# restore previous directory
	cd $prevDir
}
