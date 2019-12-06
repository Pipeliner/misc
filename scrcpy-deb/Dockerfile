FROM ubuntu:16.04
RUN apt update && apt upgrade -y && apt install -y \
      ffmpeg libsdl2-2.0-0 \
      make gcc git pkg-config ninja-build \
      libavcodec-dev libavformat-dev libavutil-dev \
      libsdl2-dev wget git checkinstall \
      python3-pip && pip3 install meson && \
      git clone https://github.com/Pipeliner/scrcpy -b patch-1 && \
      cd scrcpy && \
      wget https://github.com/Genymobile/scrcpy/releases/download/v1.10/scrcpy-server-v1.10.jar && \
      meson x --buildtype release --strip -Db_lto=true \
      -Dprebuilt_server=scrcpy-server-v1.10.jar && \
      cd x && ninja && checkinstall ninja install
                   
