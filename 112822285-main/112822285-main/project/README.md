# Look Up a Word #
#### Version: "1.0.0"
#### Video Demo: <https://youtu.be/T5U6fCdXk8g> ####
### Description:
This is a Chrome extension that helps me (and probably you) to look up a new English word without opening another tab.
As a person who speaks English as a third language, I'm often frustrated when I encounter unfamiliar words and can't understand things clearly when reading news or code-related explanations.

It can be a little annoying to have to open a new tab to look up these new words, and you might not want to use Google's automatic translation because you want the exact meaning of the word. Maybe more than definitions? That's where this little tool can help!

>The project contains four files-<index.html>, <manifest.json>, <script.js>, <style.css>.

1. The <index.html> file contains what will be displayed on the window. It mainly has an input and a button to look up. When found, use a div element to insert in.

2. The <style.css> file controls the design of the page, including things like color and font size. The extension's colors are mainly blue and grey.

3. The <script.js> file controls the mechanics behind the web page, including what will be displayed after clicking a button and how to interact with the API when sending a word to be looked up. Exclude any invalid word like one not only contains letters or the word was not found.
Get the API document and process it in JavaScript and send the useful data(the definition, synonyms) back to html file.

4. The <manifest.json> file contains information about the extension, including its name, version control, a simple description, and what will happen when the extension is opened.

I am still trying to add more features on my project(maybe database?or more information to look up?). I tried to add a db file and use python to save words that I would like to keep to my database. However, it doesn't work that well. So I consider stop it in this version. Maybe in the next version.

### Installing:
1. Download all the four files(html, json, js, css) in the project directory.
2. Open up Chrome extension("chrome://extensions")
At the top right, click More : > More tools > Extensions.
3. Turn on Developer mode.
4. Click Load unpacked.
5. Upload the directory that contains four files.
6. Click the app and the extensions at the top right and choose the chrome extension you just uploaded.
7. Test the tool!
>If you encounter any problem(Like cannot detect the normal words, still accept invalid words, the tool doesn't work...) please let me know so I could fix it and improve it.:)
### Licence
This project is licensed under the MIT License.

### Acknowledgements
* dictionaryapi
