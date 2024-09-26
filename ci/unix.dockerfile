FROM debian:bookworm-slim

# Dependencies
RUN apt update && apt upgrade
RUN apt install -y  build-essential \
    cmake \
    git  \
    wget \
    tar \
    autoconf \
    automake \
    make \
    libtool \
    pkg-config \
    python3 \
    python3-pip \
    g++ \
    gcc \
    ninja-build \
    curl \
    bash \
    zip \
    unzip \
    libx11-dev \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libgl1-mesa-dev

#Install vpckg
WORKDIR /tmp
ENV VCPKG_FORCE_SYSTEM_BINARIES=1
RUN wget -qO vcpkg.tar.gz https://github.com/microsoft/vcpkg/archive/master.tar.gz
RUN mkdir /opt/vcpkg
RUN tar -xzf vcpkg.tar.gz --strip-components=1 -C /opt/vcpkg
RUN /opt/vcpkg/bootstrap-vcpkg.sh
RUN ln -s /opt/vcpkg/vcpkg /usr/local/bin/vcpkg
RUN rm -rf /tmp/*
RUN chmod -R 777 /opt/vcpkg

ENV VCPKG_ROOT=/opt/vcpkg

#Mount current project
WORKDIR /app
