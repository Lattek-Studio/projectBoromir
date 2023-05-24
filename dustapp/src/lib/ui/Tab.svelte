<script>
    export let name = "CO2";
    export let value = {
        value: 0,
        unit: "ppm"
    };
</script>
<div class="container">
    <span class="title">{name}</span>
    <span class="value">{value.value}{value.unit}</span>
</div>
<style>
    .container{
        background-color: var(--bgLight);
        border-radius: 69rem;
        display:flex;
        gap: 1rem;
        align-items: center;
        justify-content: space-between;
        width: 100%;
    }
    span{
        padding: 1rem;
    }
    .title{
        font-weight: 400;
    }
    .value{
        background-color: var(--bgDark);
        border: 1px solid var(--accent);
        border-radius: 69rem;
        font-weight: 700;
    }
</style>