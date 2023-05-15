FROM node:alpine

RUN apk update && apk add python3
RUN apk add py3-pip

RUN apk add make

RUN npm install -g node-gyp

RUN apk add build-base


WORKDIR ./my-app

COPY ./app/package.json ./my-app/app/
WORKDIR ./my-app/app/
RUN npm install



COPY ./app/ ./my-app/app/

WORKDIR ./my-app/app/
RUN npm run build
ENV BODY_SIZE_LIMIT 0
ENV PORT 80
EXPOSE 80
CMD ["node", "build"]