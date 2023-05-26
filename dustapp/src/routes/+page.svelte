<script>
    import { Tab, Switch } from '$ui'
	import { dbStore } from '$lib/stores/db'
    import { sensorsStore, furnitureStore } from '$lib/supabase';
    import { onMount, onDestroy } from 'svelte';
    export let data = {};
    let dataInterval
    let aqi = '?'
    onMount(()=>{
        dataInterval = sensorsStore.subscribe((curr)=>{
        let temp = curr;
        data = {
            'Carbon Dioxide': {
                value: temp.CO2_ppm,
                unit: 'ppm',
                state: temp.CO2_ppm > 2000 ? 'on' : 'off'
            },
            'Temperature': {
                value: temp.average_TEMP_celsius,
                unit: '°C',
                state: temp.average_TEMP_celsius > 30 ? 'on' : 'off'
            },
            'Humidity': {
                value: temp.HUMIDITY_percent,
                unit: '%',
                state: temp.HUMIDITY_percent > 60 ? 'on' : 'off'
            },
            'Pressure': {
                value: temp.PRESSURE_pascals?.toFixed(0),
                unit: 'Pa',
                state: 'off'
            },
            'TVOC': {
                value: temp.TVOC_ppb,
                unit: 'ppb',
                state: 'off'
            }
        }
        if(typeof temp.aqi == 'number'){
            aqi = temp.aqi
        }
    });
    return dataInterval;
    })
    onDestroy(() => { 
        data = {};
    })
    function setRootColor(color){
        // Select the :root element
        if(typeof window == 'undefined') return
        const rootElement = document.documentElement;

        // Change the value of the --accent CSS variable
        rootElement.style.setProperty('--accent', color);
    }
    function getWord(aqi) {
        if (typeof aqi !== 'number') {
            setRootColor('var(--defaultAccent)');
            return '...';
        }

        if (aqi > 300) {
            setRootColor('#FF0000'); // Set color for hazardous
            return 'hazardous';
        }

        if (aqi > 200) {
            setRootColor('#990000'); // Set color for very unhealthy
            return 'very unhealthy';
        }

        if (aqi > 150) {
            setRootColor('#FF715B'); // Set color for unhealthy
            return 'unhealthy';
        }

        if (aqi > 100) {
            setRootColor('#FF715B'); // Set color for sensitive
            return 'sensitive';
        }

        if (aqi > 50) {
            setRootColor('#FF715B'); // Set color for moderate
            return 'moderate';
        }

        setRootColor('#FF715B'); // Set color for good
        return 'good';
    }

</script>
<div class="container">
    <div class="circle">
        <svg width="274" height="234" viewBox="0 0 274 234" fill="none" xmlns="http://www.w3.org/2000/svg">
            <path fill-rule="evenodd" clip-rule="evenodd" d="M270.917 163.673C265.65 190.151 252.65 214.473 233.56 233.563L229.951 229.954C249.619 207.988 261.571 179.022 261.571 147.276C261.571 78.6402 205.702 22.9999 136.785 22.9999C67.8682 22.9999 11.9999 78.6402 11.9999 147.276C11.9999 179.152 24.0498 208.224 43.8604 230.223L40.52 233.563C21.4302 214.473 8.42982 190.151 3.16294 163.673C-2.10394 137.194 0.599213 109.749 10.9306 84.8067C21.2619 59.8645 38.7575 38.5462 61.2048 23.5474C83.6521 8.54855 110.043 0.542969 137.04 0.542969C164.037 0.542969 190.428 8.54855 212.875 23.5474C235.323 38.5462 252.818 59.8645 263.15 84.8066C273.481 109.749 276.184 137.194 270.917 163.673Z" fill="var(--accent)"/>
        </svg>
        <div class="text">
            <h1 class="aqi">aqi</h1>
            <h1 class="value">{aqi}</h1>
            <h1 class="sms">{getWord(aqi)}</h1>
        </div>
    </div>

    
    <div class="items">
        {#each Object.entries(data) as [type, value]}
            <Tab name={type} value={value} state={value.state} />
        {/each}
    </div>
   

    <div class="buttons">
        <div class="button">
            <p>Win.</p>
            <Switch bind:checked={$furnitureStore.geam}/>
        </div>
        <div class="button">
            <p>Fan</p>
            <Switch bind:checked={$furnitureStore.fan}/>
        </div>
    </div>
</div>

<style>
    .items{
        display: flex;
        flex-direction: column;
        gap: 1rem;
        justify-content: center;
        align-items: center;
        min-width: min(60%, 250px);
    }

    .container{
        display: flex;
        flex-direction: column;
        align-items: center;
    }
    .circle{
        position: relative;
        margin-bottom: 1rem;
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
        white-space: nowrap
    }

    .buttons{
        display:flex;
        gap: 2rem;
    }
    .button{
        display:flex;
        align-items: center;
        justify-content: center;
        gap: 1rem;
    }
</style>
