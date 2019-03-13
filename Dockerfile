FROM debian:stretch-slim AS builder

RUN apt update
RUN apt install -y \
	build-essential \
	pkg-config \
	libgsl-dev

COPY . /src
WORKDIR /src

RUN make install

FROM debian:stretch-slim

RUN apt update
RUN apt install -y \
	libgsl2 \
	gnuplot-nox

COPY --from=builder /usr/local/bin/* /usr/local/bin/

CMD ["sh"]
