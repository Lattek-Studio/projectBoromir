<script>
  import { off } from "firebase/database";
  import { onMount } from "svelte";

    export let name = 'Carbon Dioxide'
    export let day = '27.05.2023'
    export let unit = 'ppm'
    export let data
    //set data to sin wave Array
    data = Array.from({ length: 100 }, (_, i) => ({
        data: Math.sin(i / 16)
    }))

   

    const minX = 47
    const maxX = 325
    const minY = 87
    const maxY = 187

    function getX(i) {
        return minX + (maxX - minX) / (data.length - 1) * i
    }
    let minValue, maxValue
    $: minValue = Math.min(...data.map(({ data }) => data))
    $: maxValue = Math.max(...data.map(({ data }) => data))
    function getY(value) {
        return minY + (maxY - minY) / (maxValue - minValue) * (value - minValue)
    }
    function getHour(timestamp) {
  const date = new Date(timestamp);
  const hours = date.getHours();
  const minutes = date.getMinutes();
  const formattedTime = `${hours.toString().padStart(2, '0')}:${minutes.toString().padStart(2, '0')}`;
  return formattedTime;
}
function getDate(timestamp) {
  const date = new Date(timestamp);
  const day = date.getDate();
  const month = date.getMonth();
  const year = date.getFullYear();
  const formattedDate = `${day.toString().padStart(2, '0')}.${month.toString().padStart(2, '0')}.${year.toString().padStart(2, '0')}`;
  return formattedDate;
}
let selected = 0

const minSize = 40
const maxSize = 50

function getSize(distance) {
    // return 1 / (1 + Math.exp(-distance*2));
    let unnormalized = (maxSize - minSize) / (1000) * (distance - 10)
    //map from 0 to 1
    let nromalized = 1 / (1 + Math.exp(-unnormalized))
    return nromalized
}
let interval, interval2
let offSet = 0
let points = ''
onMount(()=>{
    interval = setInterval(() => {
        selected = (selected + 1) % data.length
        // data = Array.from({ length: 100 }, (_, i) => ({
        //     data: Math.sin(i / (16 - offSet))
        // }))
        // data = data
        offSet += 0.1
    }, 5);
    interval2 = setInterval(() => {
        if(points==''){
            points='.'
        }else if(points=='.'){
            points='..'
        }else if(points=='..'){
            points='...'
        }else if(points=='...'){
            points=''
        }
    }, 100);
    return () => {
        clearInterval(interval)
        clearInterval(interval2)
    };
})
</script>
<section>
    <input type="range" min="0" max="99" bind:value={selected} class="slider">
    <p class="title">{name} ({unit})</p>
    <p class="date">{day}</p>
    <p class="load">loading{points}</p>
    <svg width="100%" viewBox="0 0 370 240" fill="none" xmlns="http://www.w3.org/2000/svg">
        <g opacity="0.6">
        <path d="M46.5 87H327.5" stroke="#DFF8EB" stroke-linecap="round"/>
        <path d="M46.5 112H327.5" stroke="#DFF8EB" stroke-linecap="round"/>
        <path d="M46.5 137H327.5" stroke="#DFF8EB" stroke-linecap="round"/>
        <path d="M46.5 162H327.5" stroke="#DFF8EB" stroke-linecap="round"/>
        <path d="M46.5 187H327.5" stroke="#DFF8EB" stroke-linecap="round"/>
        </g>

        <circle cx="335" cy="34" r="2.5" fill="white"/>
        <circle cx="343" cy="34" r="2.5" fill="white"/>
        <circle cx="351" cy="34" r="2.5" fill="white"/>


        
        {#each data as _, i}
        <line x1={getX(i)} y1={minY} x2={getX(i)} y2="1000" opacity="0" style="stroke:white;stroke-width:4" on:mouseover={()=>selected=i}/>

            {#if i == selected}
            <line x1={getX(i)} y1={minY} x2={getX(i)} y2={maxY} opacity="0.5" style="stroke:white;stroke-width:2" />

                <circle cx={getX(i)} cy={getY(data[i].data)} r="2.5" fill="var(--accent)" style="transition: all 0s ease-in"/>
            {:else}
                <circle cx={getX(i)} cy={getY(data[i].data)} r="1" fill="white" style="transition: all 0s ease-in"/>
            {/if}
            {#if i != data.length - 1}
                <line x1={getX(i)} y1={getY(data[i].data)} x2={getX(i+1)} y2={getY(data[i+1].data)} style="stroke:white;stroke-width:2" />
            {/if}
            {#if i%21 == 0}
            
            <!-- <circle cx={getX(i)} cy="200" r="2.5" fill="white"/> --> 
            <!-- {getHour(data[i].created_at)} -->
            {/if}
        {/each}
        <circle cx={getX(selected)} cy={getY(data[selected].data)} r="2.5" fill="var(--accent)" style="transition: all 0s ease-in"/>

        {#each data as _, i}
        <line x1={getX(i)} y1={minY} x2={getX(i)} y2="1000" opacity="0" style="stroke:white;stroke-width:4" on:mouseover={()=>selected=i}/>
        
        {/each}
    </svg>
</section>
    
<style>
    section{
        position: relative;
        background-color: var(--bgLight);
        border-radius: 1rem;
        width: clamp(200px, 90%, 600px);
    
    }
    p{
        position: absolute;
        margin: 0;
        padding: 0;
    }
    .title{
        top: 10%;
        left: 5%
    }
    .load{
        top: 2%;
        left: 43%
    }
    .date{
        top: 10%;
        right: 15%;
    }
    .min{
        top: 72%;
    }
    .max{
        top: 31%;
    }
    .average{
        top: 51.5%;
    }
    .nr{
        left: 1.5%;
    }


    /* The slider itself */
.slider {
    all: unset;
  -webkit-appearance: none;  /* Override default CSS styles */
  appearance: none;
  width: 76.5%; /* Full-width */
  height: 5px; /* Specified height */
  background: var(--bgDark); /* Grey background */
  outline: none; /* Remove outline */

  position: absolute;
  top: 21%;
  left: 12%;

  border-radius: 1rem;
}

/* Mouse-over effects */
.slider:hover {
  opacity: 1; /* Fully shown on mouse-over */
}

/* The slider handle (use -webkit- (Chrome, Opera, Safari, Edge) and -moz- (Firefox) to override default look) */
.slider::-webkit-slider-thumb {
  -webkit-appearance: none; /* Override default look */
  appearance: none;
  width: 5px; /* Set a specific slider handle width */
  height: 5px; /* Slider handle height */
  background: var(--accent); /* Green background */
  cursor: pointer; /* Cursor on hover */
  border-radius: 1rem;

}
.slider::-moz-range-thumb {
  -webkit-appearance: none; /* Override default look */
  appearance: none;
  width: 5px; /* Set a specific slider handle width */
  height: 5px; /* Slider handle height */
  background: var(--accent); /* Green background */
  cursor: pointer; /* Cursor on hover */
  border-radius: 1rem;

}

.hover{
    cursor: pointer;
}
</style>