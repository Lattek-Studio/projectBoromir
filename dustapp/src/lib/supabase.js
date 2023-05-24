
import { createClient } from '@supabase/supabase-js'
import { writable } from "svelte/store";

const id = 2


// Create a single supabase client for interacting with your database
export const supabase = createClient('https://supaapi.byteforce.ro/', 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyAgCiAgICAicm9sZSI6ICJzZXJ2aWNlX3JvbGUiLAogICAgImlzcyI6ICJzdXBhYmFzZS1kZW1vIiwKICAgICJpYXQiOiAxNjQxNzY5MjAwLAogICAgImV4cCI6IDE3OTk1MzU2MDAKfQ.DaYlNEoUrrEn2Ig7tqibS-PHK5vgusbcbo7X36XVt4Q')
export const sensorsStore = writable({})

function createFurniture() {
	const { subscribe, set, update } = writable({});


  const setAndSync = async (val) => {
    // set(val); // Update the local store value

    const { data, error } = await supabase
      .from('sensor_realtime')
      .update(val)
      .eq('id', id); // Assuming 'id' is the identifier for your record

    if (error) {
      console.error('Error updating data:', error.message);
      return;
    }

    console.log(data);
  };


	return {
		subscribe,
		setDB: (val) => set(val),
		set: setAndSync,
		reset: () => set({})
	};
}

export const furnitureStore = createFurniture()
try{
    (async () => {
        const { data, error } = await supabase
    .from('sensor_realtime')
    .select('*')
    .eq('id', id)
    if(error){
        throw(error)
    }
    console.log(data)
    if(data){
        sensorsStore.set(data[0])
        furnitureStore.setDB({
          fan: data[0].fan,
          geam: data[0].geam
        })
    }
    })();
}catch(e){
    console.log(e)
}
const channel = supabase
  .channel('sensor_realtime')
  .on(
    'postgres_changes',
    {
      event: 'UPDATE',
      schema: 'public',
    },
    (payload) => {
        if (payload.new.id === id) {
          console.log(payload.new);
          // Assuming sensorsStore is defined and represents your data store
          sensorsStore.set(payload.new);
          furnitureStore.setDB({
            fan: payload.new.fan,
            geam: payload.new.geam
          })
        }
    }
  )
  .subscribe()
