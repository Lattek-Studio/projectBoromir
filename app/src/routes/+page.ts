export const prerender = false;

import { authHandlers } from "$stores/auth";

await authHandlers.login();