FROM silkeh/clang:latest as build

WORKDIR /app

COPY . .

RUN apt-get update && \
apt-get install -y \
libcpprest-dev libboost-all-dev openssl libsodium-dev libopus-dev libpthread-stubs0-dev && \
wget -O dpp.deb https://dl.dpp.dev/ && \
dpkg -i dpp.deb && \
apt --fix-broken install && \
cmake . && \
make

FROM alpine:latest as deploy

COPY --from=build /app/domain-checker .

ENTRYPOINT [ "./domain-checker" ]