Package: libupnp:x64-linux@1.14.18

**Host Environment**

- Host: x64-linux
- Compiler: GNU 13.2.0
-    vcpkg-tool version: 2024-11-12-eb492805e92a2c14a230f5c3deb3e89f6771c321
    vcpkg-scripts version: cd124b84f 2024-11-29 (19 minutes ago)

**To Reproduce**

`vcpkg install `

**Failure logs**

```
Downloading pupnp-pupnp-release-1.14.18.tar.gz
Failed to download pupnp-pupnp-release-1.14.18.tar.gz.
If you are using a proxy, please ensure your proxy settings are correct.
Possible causes are:
1. You are actually using an HTTP proxy, but setting HTTPS_PROXY variable to `https//address:port`.
This is not correct, because `https://` prefix claims the proxy is an HTTPS proxy, while your proxy (v2ray, shadowsocksr, etc...) is an HTTP proxy.
Try setting `http://address:port` to both HTTP_PROXY and HTTPS_PROXY instead.
2. If you are using Windows, vcpkg will automatically use your Windows IE Proxy Settings set by your proxy software. See, https://github.com/microsoft/vcpkg-tool/pull/77
The value set by your proxy might be wrong, or have same `https://` prefix issue.
3. Your proxy's remote server is our of service.
If you've tried directly download the link, and believe this is not a temporay download server failure, please submit an issue at https://github.com/Microsoft/vcpkg/issues
to report this upstream download server failure.
error: File does not have the expected hash:
url: https://github.com/pupnp/pupnp/archive/release-1.14.18.tar.gz
File: /home/mwiner/libs/vcpkg/downloads/pupnp-pupnp-release-1.14.18.tar.gz.547111.part
Expected hash: 0d2339ed9de8c2bb23ef378e83f8254f42247dcf0e5e15858a607e0bcf4216ab5d5f3e6d907f8be73dc4eb80f5d7b4a96af42f61870999c458b121f3894b76c3
Actual hash: 68973e0e5a8f9e64b2311246b7924b0837fd2c7ef30483d3d93ebfeee62bc2293760209d8a5213c0456ce5c37f9f32a6038c9e5d8b461670ba6073db8c2f1394
CMake Error at scripts/cmake/vcpkg_download_distfile.cmake:231 (message):
  Download failed, halting portfile.
Call Stack (most recent call first):
  scripts/cmake/vcpkg_from_github.cmake:106 (vcpkg_download_distfile)
  ports/libupnp/portfile.cmake:1 (vcpkg_from_github)
  scripts/ports.cmake:196 (include)



```

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "name": "mediamanagerplusplus",
  "version-string": "0.1.0",
  "dependencies": [
    "ftxui",
    "libupnp"
  ]
}

```
</details>
