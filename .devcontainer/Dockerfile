FROM mcr.microsoft.com/devcontainers/cpp:focal as skyfire_dev

RUN apt update  -y
RUN apt upgrade -y
RUN apt install -y autoconf libtool make cmake clang
RUN apt install -y git patch wget links zip unzip openssl
RUN apt install -y libssl-dev  libreadline-dev zlib1g-dev 
RUN apt install -y libbz2-dev git-core libace-dev libncurses5-dev
RUN apt install -y libmysqlclient-dev