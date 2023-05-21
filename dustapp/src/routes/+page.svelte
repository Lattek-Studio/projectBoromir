<script>
    import { Tab } from '$ui'
    import { sensors } from '$lib/supabase';
    
</script>
<h1>Dashboard v5</h1>
<!-- {JSON.stringify($sensors)} -->
{#if $sensors != 0}
    <div class="container">
        {#each Object.entries($sensors) as [type, value]}
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
