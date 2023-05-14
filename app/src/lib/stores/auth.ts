import { signInAnonymously } from "firebase/auth";
import { writable } from "svelte/store";
import { auth } from "$lib/firebase";

export const authStore = writable({
    isLoading: true,
    currentUser: null
})

export const authHandlers = {
    login: async ()=>{
        await signInAnonymously(auth)
    }
}

auth.onAuthStateChanged((user) => {
    authStore.update((curr) => {
        return { ...curr, isLoading: false, currentUser: user };
    });
});