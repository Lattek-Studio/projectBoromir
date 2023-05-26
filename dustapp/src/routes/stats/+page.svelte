<script>
    import { Tab, Switch, Week, Graph } from '$ui'
	import { dbStore } from '$lib/stores/db'
    import { sensorsStore, furnitureStore } from '$lib/supabase';
    import { onMount, onDestroy } from 'svelte';
export let data
    let selected = 0
   const selections = [
    {
        name: 'Carbon Dioxide',
        unit: 'ppm',
        code: 'CO2_ppm'
    },
    {
        name: 'Temperature',
        unit: '°C',
        code: 'average_TEMP_celsius'
    },
    {
        name: 'Humidity',
        unit: '%',
        code: 'HUMIDITY_percent'
    },
    {
        name: 'Pressure',
        unit: 'Pa',
        code: 'PRESSURE_pascals'
    },
    {
        name: 'TVOC',
        unit: 'ppb',
        code: 'TVOC_ppb'
    }
   ]
function getData(selected){
    const info = data.data.map(({ created_at, [selections[selected].code] : value }) => ({ created_at, data: value }))
    return info
}
</script>
{JSON.stringify(data.data.map(({ created_at, [selections[selected].code] : value }) => ({ created_at, data: value }))[0])}
<div class="container">
    <div class="circle">
        <svg width="274" height="234" viewBox="0 0 274 234" fill="none" xmlns="http://www.w3.org/2000/svg">
            <path fill-rule="evenodd" clip-rule="evenodd" d="M270.917 163.673C265.65 190.151 252.65 214.473 233.56 233.563L229.951 229.954C249.619 207.988 261.571 179.022 261.571 147.276C261.571 78.6402 205.702 22.9999 136.785 22.9999C67.8682 22.9999 11.9999 78.6402 11.9999 147.276C11.9999 179.152 24.0498 208.224 43.8604 230.223L40.52 233.563C21.4302 214.473 8.42982 190.151 3.16294 163.673C-2.10394 137.194 0.599213 109.749 10.9306 84.8067C21.2619 59.8645 38.7575 38.5462 61.2048 23.5474C83.6521 8.54855 110.043 0.542969 137.04 0.542969C164.037 0.542969 190.428 8.54855 212.875 23.5474C235.323 38.5462 252.818 59.8645 263.15 84.8066C273.481 109.749 276.184 137.194 270.917 163.673Z" fill="#FF715B"/>
        </svg>
        <div class="text">
            <h1><span>{selections[selected].name}</span> History</h1>
        </div>
    </div>
<div class="buttons">
    {#each selections as selection, i}
        <div class="tag {selected==i?'selected':''}" on:click={() => selected = i}>{selection.name}</div>
    {/each}
</div>

<Graph name={selections[selected].name} unit={selections[selected].unit} data={getData(selected)}/>

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
    }
    .text{
        position:absolute;
        top: 50%;
        left: 50%;
        transform: translate(-50%, -35%);
        text-align: center;
    }

    h1{
        font-size: 1.5rem;
        font-weight: 400;
    }

    span{
        white-space: nowrap;
        /* border-bottom: 0.25rem solid var(--accent); */
        font-weight: 700;
    }

    /* width */
::-webkit-scrollbar {
  width: 2px;
  height: 2px;
}

/* Track */
::-webkit-scrollbar-track {
  background: white;
}

/* Handle */
::-webkit-scrollbar-thumb {
  background: var(--gray);
  transition: all 0.2s ease-in-out;
  border-radius: 1rem;
}

/* Handle on hover */
::-webkit-scrollbar-thumb:hover {
  background: var(--accent);
}


    .buttons{
        overflow: auto;
        white-space: nowrap;
        max-width: 400px;

    }
    .tag{
        background-color: var(--bgLight);
        padding: 0.5rem 1rem;
        border-radius: 69rem;
        border: 1px solid transparent;
        transition: all 0.2s ease-in-out;

        display: inline-block;
    }
    .tag.selected{
        background-color: var(--bgDark);
        border: 1px solid var(--accent);
        /* font-weight: 700; */
    }
</style>
