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
            'temperature': {
                value: temp.average_TEMP_celsius,
                unit: '°C'
            },
            'humidity': {
                value: temp.HUMIDITY_percent,
                unit: '%'
            },
            'pressure': {
                value: temp.PRESSURE_pascals,
                unit: 'Pa'
            },
            'particles': {
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
<h1>Dashboard v4</h1>
<!-- {JSON.stringify(data)} -->
{#if data != 0}
    <div class="container">
        {#each Object.entries(data) as [type, value]}
            <Tab name={type} value={value} />
        {/each}
    </div>
{:else}
        <p>Loading...</p>
{/if}
<style>
    .container{
        display: flex;
        gap: 1rem;
        flex-wrap: wrap;
    }
</style>
