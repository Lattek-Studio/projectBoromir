<script>
    import { page } from '$app/stores'

    let path;
    $: path = $page.url.pathname;
</script>
<nav>
    <div class="nav">
        <div class="{path=='/app'?'active':''} title">
            <img src="/favicon.png" />
            <a href="/app">Dust</a>
        </div>
        <div class="{path=='/app/dashboard'?'active':''}">
            <img src="/dashboard.png" />
            <a href="/app/dashboard">Dashboard</a>
        </div>
        <div class="{path=='/app/statistics'?'active':''}">
            <img src="/statistics.png" />
            <a href="/app/statistics">Statistics</a>
        </div>
        <div class="{path=='/app/performance'?'active':''}">
            <img src="/performance.png" />
            <a href="/app/performance">Performance</a>
        </div>
        <div class="{path=='/app/settings'?'active':''}">
            <img src="/settings.png" />
            <a href="/app/settings">Settings</a>
        </div>
    </div>
    <div class="app">
        <slot />
    </div>
</nav>
<style>
    :global(*){
        outline: 1px solid blue;
    }
    nav{
        display:grid;
        grid-template-columns: clamp(200px, 15vw, 600px) auto;
    }
    img{
        height: 1.5rem;
    }
    .nav{
        display:flex;
        flex-direction:column;
        border-right: 1px solid var(--gray);
        padding: 1rem 2rem;
        min-height: 100vh;
        background-color: red;
    }
    .nav > div{
        display:flex;
        align-items:center;
        gap: 1rem;
        margin-bottom: 1rem;
    }
    .nav > div > a{
        display: inline;
        text-decoration: none;
        color: inherit;
    }
    .title > a{
        font-size: 1.5rem;
        font-weight: bold;
    }
    .title{
        display: block;
        padding-bottom: 5rem;
    }
    .app{
        padding: 1rem;
    }
    @media (max-width: 600px){
        nav{
            display: grid;
            grid-template-columns: 1fr;
            grid-template-rows: auto 10vh;
            height: 100vh;
        }
        .app{
            grid-column-start: 1;
            grid-column-end: 1;
        }
        .nav{
            min-height: 10vh;
            grid-row-start: 2;
            grid-row-end: 2;
            display: flex;
            flex-direction: row;
        }
        .nav > div{
            margin-bottom: 0;
        }
        .nav > div > img{
            display: none;
        }
        .title{
            padding-bottom: 0;
            display: none;
        }
        .title > a{
            display: none;
        }
    }
</style>