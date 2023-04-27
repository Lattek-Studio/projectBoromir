<script>
    export let name;
    export let value;
</script>
<div class="container">
    <h1>{name}</h1>
    <p>{value.value}{value.unit}</p>
    <div class="bar">

    </div>
</div>
<style>
    .container{
        background-color: var(--bgLight);
        padding: 1rem;
        border-radius: 0.5rem;
        /* margin-block: 1rem; */
        width: fit-content;
        display:flex;
        gap: 1rem;
        align-items: center;
    }
    h1{
        border-right: 1px solid var(--gray);
        width: fit-content;
        padding-right: 1rem;
    }
</style>