
import { createClient } from '@supabase/supabase-js'
import { writable } from "svelte/store";

// Create a single supabase client for interacting with your database
export const supabase = createClient('https://supaapi.byteforce.ro/', 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyAgCiAgICAicm9sZSI6ICJhbm9uIiwKICAgICJpc3MiOiAic3VwYWJhc2UtZGVtbyIsCiAgICAiaWF0IjogMTY0MTc2OTIwMCwKICAgICJleHAiOiAxNzk5NTM1NjAwCn0.dc_X5iR_VP_qT0zsiyj_I_OZ2T9FtRU2BBNWN8Bu4GE')
export const sensorsStore = writable({})

try{
    (async () => {
        const { data, error } = await supabase
    .from('sensor_realtime')
    .select('*')
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
        console.log(payload.new)
        sensorsStore.set(payload.new)
    }
  )
  .subscribe()

  function translateData(temp){
    delete temp.id
    temp['temperature'] = temp['average_TEMP_celsius'];
    temp['pressure'] = temp['PRESSURE_pascals'];
    temp['particles'] = temp['PARTICLES_ugm3'];
    temp['humidity'] = temp['HUMIDITY_percent'];

    delete temp['bmp280_TEMP_celsius'];
    delete temp['PRESSURE_pascals'];
    delete temp['PARTICLES_ugm3'];
    delete temp['dht_TEMP_celsius'];
    delete temp['average_TEMP_celsius'];
    delete temp['HUMIDITY_percent'];

    const units = {
        CO2: "ppm",
        particles: "µg/m3",
        humidity: "%",
        temperature: "°C",
        pressure: "Pa",
        timestamp: '',
    }

    Object.keys(temp).forEach(key => {
        temp[key] = {
            value: temp[key],
            unit: units[key]
        }
    })

    return temp;
}

export const sensors = writable({})

//update sensors with translate of data form sensors store on change 
sensorsStore.subscribe((value) => {
    sensors.set(translateData(value))
})
// setInterval(async ()=>{
//     let { data, error } = await supabase.from('sensor_realtime').select('*')
//     if (error) console.log(error)
//     if (data) sensorsStore.set(data[0])
// }, 1000)