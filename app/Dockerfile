FROM node:alpine

RUN apk update && apk add python3
RUN apk add py3-pip

RUN apk add make

RUN npm install -g node-gyp

RUN apk add build-base

COPY ./app/package.json .
RUN npm install

COPY ./app/ ./
COPY ./app/sveltenode.config.js ./svelte.config.js
RUN npm run build
ENV BODY_SIZE_LIMIT 0
ENV PORT 80
EXPOSE 80
CMD ["npm", "run", "start"]