
//Insert a word's definition to the webpage
function wordtemplate(wordinfo) {
	let number = wordinfo.meanings.length
	var inject_def ='';
	//check the definition/synonyms/antonyms that word has
	for (let i = 0; i < number; i++)
	{
		synonyms = `${wordinfo.meanings[i].synonyms}`;
		antonyms = `${wordinfo.meanings[i].antonyms}`;
		inject_def += `<ul>${wordinfo.meanings[i].partOfSpeech}<li>${wordinfo.meanings[i].definitions[0].definition}</li></ul>`;
		if (synonyms)
		{
			inject_def += `<div id = "synonym">Synonyms :${wordinfo.meanings[i].synonyms}</div>`;
		}
		if (antonyms)
		{
			inject_def += `<div id = "synonym">Antonyms :${wordinfo.meanings[i].antonyms}</div><br>`;
		}

	}

	return inject_def;
}
//check if word does exist

function isword(res) {
	//map() only applies to array in Javascript, if the word was not found, the api document will be an object
	if (res.hasOwnProperty('message'))
	{
		return false;
	}
	return true;
}

//check the input is not empty first and check if the input only has letter
function isletter(check) {
	check = check.toLowerCase();
	if (check === "")
	{
		return false;
	}
	for (let i = 0; i < check.length; i++)
	{
		if (check[i] < 'a' || check[i] > 'z')
		{
			return false;
		}
	}
	return true;
}


// mouse movement to change color on the button
document.querySelector('button').addEventListener('mouseover', function(){
	document.querySelector('button').style.backgroundColor = "#B3B3B3";
});
document.querySelector('button').addEventListener('mouseout', function(){
	document.querySelector('button').style.backgroundColor = "#797979";
});

//Look up a word
document.querySelector('#check').addEventListener('click', async function() {
	let check = document.querySelector('input').value;
	document.querySelector(".searchword").innerHTML='';

	if (isletter(check) == false)
	{
		document.querySelector("#definition").innerHTML = "Invalid";
	}
	else
	{
		document.querySelector("#definition").innerHTML= "Translating...";
		let word = document.querySelector('input').value.toLowerCase();
		let response = await fetch(`https://api.dictionaryapi.dev/api/v2/entries/en/${word}`);
		let res = await response.json();
		//check the word was found or not
		if (isword(res) == false)
		{
			document.querySelector("#definition").innerHTML = "Wrong word.";
		}
		else
		{
			document.querySelector(".searchword").innerHTML= `${word}`;
			document.querySelector("#definition").innerHTML= `${res.map(wordtemplate).join('')}`;
		}
	}

})

