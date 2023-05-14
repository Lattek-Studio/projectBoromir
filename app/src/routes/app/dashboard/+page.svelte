<script>
    import { Tab } from '$ui'
	import { dbStore } from '$lib/stores/db'
    export let data;
    dbStore.subscribe((curr) => {
		console.log('CURR', curr);
        if (Object.keys(curr).length === 0) return;
		const units = {
            CO2: "ppm",
            TVOC: "µg/m3",
            humidity: "%",
            temperature: "°C",
            pressure: "Pa",
            timestamp: '',
        }
        Object.keys(curr).forEach(key => {
            curr[key] = {
                value: parseFloat(curr[key]).toFixed(2),
                unit: units[key]
            }
        })
        curr.humidity.value = parseFloat(curr.humidity.value).toFixed(2);
        curr.temperature.value = parseFloat(curr.temperature.value).toFixed(2);
        // curr.pressure.value = parseFloat(curr.pressure.value).toFixed(2);
        data = curr;
	});
    data = {
        "Pressure": {
            value: 100757.7,
            unit: "Pa"
        },
        "Particles": {
            value: 3,
            unit: "ugm3"
        },
        "Humidity": {
            value: 2.3,
            unit: "%"
        },
        "Temperature": {
            value: 22.975,
            unit: "°C"
        },
    }
</script>
<h1>Dashboard</h1>
<div class="container">
    {#each Object.entries(data) as [type, value]}
        <Tab name={type} value={value} />
    {/each}
</div>
<style>
    .container{
        display: flex;
        gap: 1rem;
        flex-wrap: wrap;
    }
</style>
