FROM debian:stretch

WORKDIR /build

RUN apt-get update && apt-get install -y \
  build-essential \
  gnu-efi

CMD make clean && make
