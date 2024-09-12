FROM alpine:3.20 AS builder

WORKDIR /app

COPY . .

RUN apk add --no-cache protobuf-c make gcompat

ENTRYPOINT ["/app/out/server"]
