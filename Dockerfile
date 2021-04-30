FROM selenium/standalone-chrome-debug:latest as dev

USER root

ARG DEV_DEPENDENCIES="git ca-certificates gdb net-tools"
ARG BUILD_DEPENDENCIES="build-essential cmake"
ARG THIRD_PARTY_DEPENDENCIES="libcairo2-dev libgraphicsmagick1-dev"
ARG TEST_DEPENDENCIES="libpng-dev"

WORKDIR /srv/app

COPY docker-start-script.sh .

RUN set -ex \
    && apt update -y \
    # install system dependencies
    && DEBIAN_FRONTEND=noninteractive apt install -y \
        ${DEV_DEPENDENCIES} \
        ${BUILD_DEPENDENCIES} \
        ${THIRD_PARTY_DEPENDENCIES} \
        ${THIRD_PARTY_DEPENDENCIES} \
    # install io2d
    && mkdir -p /opt/c++ \
    && cd /opt/c++ \
    && git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl \
    && cd P0267_RefImpl \
    && mkdir Debug \
    && cd Debug \
    && cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" .. \
    && cmake --build . \
    && make install \
    # clean up
    && apt autoremove \
    && apt clean \
    && rm -rf ~/.cache/* /var/lib/apt/lists/* /var/cache/apt/* /tmp/*

# VNC server
EXPOSE 5900

CMD bash -c "./docker-start-script.sh && sleep infinity"



FROM dev as run_app

WORKDIR /srv/app/build

COPY . ..

RUN cmake .. && make

CMD bash -c "../docker-start-script.sh && ./OSM_A_star_search -f ../map.osm"
