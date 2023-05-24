
import { createClient } from '@supabase/supabase-js'
import { writable } from "svelte/store";

// Create a single supabase client for interacting with your database
export const supabase = createClient('https://supaapi.byteforce.ro/', 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyAgCiAgICAicm9sZSI6ICJhbm9uIiwKICAgICJpc3MiOiAic3VwYWJhc2UtZGVtbyIsCiAgICAiaWF0IjogMTY0MTc2OTIwMCwKICAgICJleHAiOiAxNzk5NTM1NjAwCn0.dc_X5iR_VP_qT0zsiyj_I_OZ2T9FtRU2BBNWN8Bu4GE')
export const sensorsStore = writable({})
const id = 1
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
        }
    }
  )
  .subscribe()

// setInterval(async ()=>{
//     let { data, error } = await supabase.from('sensor_realtime').select('*')
//     if (error) console.log(error)
//     if (data) sensorsStore.set(data[0])
// }, 1000)