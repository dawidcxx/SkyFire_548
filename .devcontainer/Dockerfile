FROM mcr.microsoft.com/devcontainers/cpp:focal as skyfire_dev

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.22.2"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# Dependencies
RUN apt update  -y
RUN apt upgrade -y
RUN apt install -y autoconf libtool make cmake clang
RUN apt install -y git patch wget links zip unzip openssl
RUN apt install -y libssl-dev  libreadline-dev zlib1g-dev 
RUN apt install -y libbz2-dev git-core libace-dev libncurses5-dev
RUN apt install -y libmysqlclient-dev 

# Optional tools
RUN apt install -y mycli tldr

COPY ./install-dotnetcore.sh /tmp/
RUN bash /tmp/install-dotnetcore.sh