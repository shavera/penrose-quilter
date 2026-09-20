FROM ubuntu:26.04

ENV DEBIAN_FRONTEND=noninteractive

RUN mv /etc/apt/apt.conf.d/docker-clean /etc/apt/apt.conf.d/docker-clean.disabled

RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
      build-essential \
      ca-certificates \
      curl \
      git \
      python3 \
      wget

ARG CMAKE_VERSION="4.4.3"
ARG CMAKE_ARCH="linux-x86_64"

RUN <<EOD
  set -e
  mkdir -p /tmp/cmake-install
  cd /tmp/cmake-install
  wget --no-verbose "https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-${CMAKE_ARCH}.sh"
  curl -L "https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-SHA-256.txt" -o sha256.txt
  ls
  sha256sum --ignore-missing -c sha256.txt
  sh cmake-${CMAKE_VERSION}-${CMAKE_ARCH}.sh --prefix=/usr/local --exclude-subdir
  cd /tmp
  rm -rf /tmp/cmake-install
EOD

RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get install -y --no-install-recommends \
      qt6-base-dev

# Add Developer QoL features
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get install -y --no-install-recommends \
      gammaray \
      gdb \
      gpg \
      less \
      micro \
      ninja-build

RUN mv /etc/apt/apt.conf.d/docker-clean.disabled /etc/apt/apt.conf.d/docker-clean