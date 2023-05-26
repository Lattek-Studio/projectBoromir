import { getAllData } from '$lib/supabase';
export function load(){
    return {
        data: getAllData()
    }
}