<script>
    import { page } from '$app/stores'
    import { goto } from '$app/navigation';
    let path;
    $: path = $page.url.pathname;
</script>
<nav>
    <div class="nav">
        <div class="{path=='/app'?'active':''} title" on:click={()=>goto("/app")}>
            <img src="/favicon.png" />
            <a href="/app">Dust</a>
        </div>
        <div class="{path=='/app/dashboard'?'active':''} item" on:click={()=>goto("/app/dashboard")}>
            <img src="/dashboard.png" />
            <a href="/app/dashboard">Dashboard</a>
        </div>
        <div class="{path=='/app/statistics'?'active':''} item" on:click={()=>goto("/app/statistics")}>
            <img src="/statistics.png" />
            <a href="/app/statistics">Statistics</a>
        </div>
        <div class="{path=='/app/performance'?'active':''} item" on:click={()=>goto("/app/performance")}>
            <img src="/performance.png" />
            <a href="/app/performance">Performance</a>
        </div>
        <div class="{path=='/app/settings'?'active':''} item" on:click={()=>goto("/app/settings")}>
            <img src="/settings.png" />
            <a href="/app/settings">Settings</a>
        </div>
    </div>
    <div class="app">
        <div class="bar">
            <img class="settings" src="/settings.png"  on:click={()=>goto("/app/settings")}/>
            <div class="{path=='/app'?'active':''} title" on:click={()=>goto("/app")}>
                <img src="/favicon.png" />
                <a href="/app">Dust</a>
            </div>
            <img class="notifications" src="/notifications.png" />
        </div>
        <div class="content">
            <slot />
        </div>
    </div>
</nav>
<style>
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
    }
    .item, .title{
        display:flex;
        align-items:center;
        gap: 1rem;
        margin-bottom: 1rem;
    }
    a{
        display: inline;
        text-decoration: none;
        color: inherit;
    }
    .title > a{
        font-size: 1.5rem;
        font-weight: bold;
    }
    .title{
        display: flex;
        margin-bottom: 4rem;
    }
    .nav > div:not(.title){
        opacity: 0.5;
    }
    .nav > div.active{
        /* border-bottom: 1px solid var(--accent); */
        opacity: 1;
    }
    .content{
        padding: 1rem;
    }
    .bar{
        display: flex;
        justify-content: flex-end;
        padding: 1rem;
    }
    .bar > .title{
        display: none;
        margin-bottom: 0;
    }
    .bar > .settings{
        display: none;
    }
    .nav > div{
        transition: all 0.2s ease-in-out;
    }
    .nav > div:not(.title):hover{
        cursor: pointer;
        transform: scale(1.1);
        opacity: 1;
    }
    @media (max-width: 600px){
        nav{
            display: grid;
            grid-template-columns: 1fr;
            grid-template-rows: auto 7.5vh;
            height: 100vh;
        }
        .app{
            grid-column-start: 1;
            grid-column-end: 1;
        }
        .nav{
            min-height: 0;
            grid-row-start: 2;
            grid-row-end: 2;
            display: flex;
            flex-direction: row;
            justify-content: space-around;
            border-right: 0;
            border-top: 1px solid var(--gray);
        }
        .nav > div{
            margin-bottom: 0;
            padding: 0;
        }
        .nav > div > a{
            display: none;
        }
        .title{
            display: none;
        }
        .bar{
            justify-content: space-between;
        }
        .bar > .title{
            display: flex;
        }
        .bar > .settings, .bar > .notifications{
            display: block;
        }
    }
</style>