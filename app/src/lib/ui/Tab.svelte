<script>
    export let name = "CO2";
    export let value = {
        value: 0,
        unit: "ppm"
    };
</script>
<div class="container">
    <p>{name}</p>
    <h2>{value.value}{value.unit}</h2>
    <div class="bar">

    </div>
</div>
<style>
    .container{
        background-color: var(--bgLight);
        padding-inline: 1rem;
        border-radius: 0.5rem;
        /* margin-block: 1rem; */
        width: fit-content;
        display:flex;
        gap: 1rem;
        align-items: center;
    }
    p{
        border-right: 1px solid var(--gray);
        width: fit-content;
        padding-right: 1rem;
    }
</style>