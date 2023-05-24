<script>
    import { Tab } from '$ui'
	import { dbStore } from '$lib/stores/db'
    import { sensorsStore } from '$lib/supabase';
    import { onMount, onDestroy } from 'svelte';
    export let data = 0;
    let dataInterval
    onMount(()=>{
        dataInterval = sensorsStore.subscribe((curr)=>{
        let temp = curr;
        data = {
            'Temperature': {
                value: temp.average_TEMP_celsius,
                unit: '°C'
            },
            'Humidity': {
                value: temp.HUMIDITY_percent,
                unit: '%'
            },
            'Pressure': {
                value: temp.PRESSURE_pascals.toFixed(0),
                unit: 'Pa'
            },
            'Particles': {
                value: temp.PARTICLES_ugm3,
                unit: 'ug/m3'
            }
        }
    });
    })
    onDestroy(() => { 
        data = 0;
    })
</script>

<div class="container">
    <div class="circle">
        <svg width="274" height="234" viewBox="0 0 274 234" fill="none" xmlns="http://www.w3.org/2000/svg">
            <path fill-rule="evenodd" clip-rule="evenodd" d="M270.917 163.673C265.65 190.151 252.65 214.473 233.56 233.563L229.951 229.954C249.619 207.988 261.571 179.022 261.571 147.276C261.571 78.6402 205.702 22.9999 136.785 22.9999C67.8682 22.9999 11.9999 78.6402 11.9999 147.276C11.9999 179.152 24.0498 208.224 43.8604 230.223L40.52 233.563C21.4302 214.473 8.42982 190.151 3.16294 163.673C-2.10394 137.194 0.599213 109.749 10.9306 84.8067C21.2619 59.8645 38.7575 38.5462 61.2048 23.5474C83.6521 8.54855 110.043 0.542969 137.04 0.542969C164.037 0.542969 190.428 8.54855 212.875 23.5474C235.323 38.5462 252.818 59.8645 263.15 84.8066C273.481 109.749 276.184 137.194 270.917 163.673Z" fill="#FF715B"/>
        </svg>
        <div class="text">
            <h1 class="aqi">aqi</h1>
            <h1 class="value">169</h1>
            <h1 class="sms">unhealthy</h1>
        </div>
    </div>

    {#if data != 0}
        <div class="items">
            {#each Object.entries(data) as [type, value]}
                <Tab name={type} value={value} />
            {/each}
        </div>
    {:else}
            <p>Loading...</p>
    {/if}
</div>

    

<style>
    .items{
        display: flex;
        flex-direction: column;
        gap: 1rem;
        justify-content: center;
        align-items: center;
        width: 60%;
    }

    .container{
        display: flex;
        flex-direction: column;
        align-items: center;
    }
    .circle{
        position: relative;
    }
    .text{
        position:absolute;
        top: 50%;
        left: 50%;
        transform: translate(-50%, -50%);
        text-align: center;
        line-height: 0.1;
    }
    .aqi{
        font-size: 2rem;
        font-weight: 300;
        text-transform: uppercase;
    }
    .value{
        font-size: 4rem;
        font-weight: 700;
    }
    .sms{
        font-size: 1.5rem;
        font-weight: 300;
    }
</style>
