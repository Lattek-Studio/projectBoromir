<script>
    import { authStore } from '$lib/stores/auth'
	import { dbStore } from '$lib/stores/db'
	let uid;
	authStore.subscribe((curr) => {
		console.log('CURR', curr);
		uid = curr?.currentUser?.uid;
	});
	let data
	dbStore.subscribe((curr) => {
		console.log('CURR', curr);
		data = curr;
	});
</script>
<section>
	<h1>Welcome to projectBoromir</h1>

	<p>This project is on its way to beeing finished...</p>
	<p>...but it's not there yet.</p>

	<p>Your user id is <span>{uid}</span></p>
	{#each Object.keys(data) as key}
		<p><span>{key}</span> is <span>{data[key]}</span></p>
	{/each}
</section>