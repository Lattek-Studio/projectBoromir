
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


(async () => {
  try {
 
const column_name = 'HUMIDITY_percent'
const end_time = '2023-05-12 14:35:38.301766+00'
const start_time = '2023-05-12 10:48:42.09073+00'
const table_name = 'sensors_arch'
    let { data, error } = await supabase
  .rpc('get_median_value', {
    column_name, 
    end_time, 
    start_time, 
    table_name
  })
console.log(data)


  } catch (e) {
      // Deal with the fact the chain failed
  }
  // `text` is not available here
})();

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

export async function waitOneSecond(){
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve('resolved');
    }, 1000);
  });
}
  export async function getAllData(){
    const { data, error } = await supabase
    .from('dust_arch')
    .select('*')
    .order('created_at', { ascending: false })
    .limit(100)

    if(error){
        throw(error)
    }
    data.map((data)=>{
        data.PRESSURE_pascals = data.PRESSURE_pascals/1000
    })
    await waitOneSecond()
    data.reverse()
    return data
  }