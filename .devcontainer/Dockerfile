FROM ubuntu:26.04

RUN mv /etc/apt/apt.conf.d/docker-clean /etc/apt/apt.conf.d/docker-clean.disabled

RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
      curl \
      gpg \
      git \
      build-essential \
      less \
      micro \
      ninja-build \
      wget

ARG CMAKE_VERSION="4.4.3"
ARG CMAKE_ARCH="linux-86_64"

RUN <<EOD
  mkdir -p /tmp/cmake-install
  cd /tmp/cmake-install
  curl -L "https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-${CMAKE_ARCH}.sh" -o cmakeinstall.sh
  curl -L "https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-SHA-256.txt" -o sha256.txt
  sha256sum --ignore-missing -c sha256.txt && \
  sh cmakeinstall.sh --prefix=/usr/local --exclude-subdir && \
  rm cmakeinstall.sh sha256.txt
  cd /tmp
  rm -rf /tmp/cmake-install
EOD

RUN <<EOL
  mkdir -p /tmp/qt-install
  cd /tmp/qt-install
  curl -OL https://download.qt.io/official_releases/online_installers/qt-online-installer-linux-x64-online.run
  qt-online-linux-installer-x64-online.run install --root /opt/qt6 --accept-licenses --default-answer --confirm-command install qt6.11.2-full-dev
  cd /tmp
  rm -rf /tmp/qt-install
EOL