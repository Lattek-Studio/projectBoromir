FROM node:alpine

WORKDIR /app

COPY package*.json ./
RUN npm install

COPY . .

RUN npm run build

ENV BODY_SIZE_LIMIT 0
ENV PORT 80
EXPOSE 80

CMD ["node", "build"]