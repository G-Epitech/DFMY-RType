FROM alpine

RUN apk add --no-cache pipx make git coreutils clang-extra-tools


RUN pipx install --global cpplint
