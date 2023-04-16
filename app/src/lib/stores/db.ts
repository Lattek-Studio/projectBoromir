import { writable } from "svelte/store";
import { db } from '$lib/firebase'

export const dbStore = writable({})
import { ref, onValue } from "firebase/database";
const dataRef = ref(db, 'data')

// Attach an asynchronous callback to read the data at our posts reference
onValue(dataRef, (snapshot) => {
    dbStore.set(snapshot.val())
});