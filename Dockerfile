FROM python:3.7-alpine
WORKDIR /usr/src/app
RUN apk add --no-cache gcc musl-dev linux-headers
COPY ./src .

