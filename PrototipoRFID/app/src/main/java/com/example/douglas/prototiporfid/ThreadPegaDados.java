package com.example.douglas.prototiporfid;

import android.content.Context;
import android.net.Uri;
import android.os.AsyncTask;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

/**
 * Created by douglas on 11/10/14.
 * Parte mais hardcore do codigo. Essa é thread que é chamada para pegar os dados do servidor.
 */
public class ThreadPegaDados extends AsyncTask<String, Void, String[]> {

    Context mContext;
    View mRootView;

    //Recebe algumas informacoes que sao usadas depois de pegar os dados do servidor.
    public ThreadPegaDados(Context context,View rootView){
        mContext=context;
        mRootView=rootView;
    }

    //Funcao que pega o Json que foi recebido do servidor e transfomra em um array de strings para serem postas na lista. Recebe como argumento a string do json "cru"
    private String[] getPosFromJSON(String posJsonStr) throws JSONException {
        Log.d("TRETA","Recebeu string Json "+posJsonStr);
        //Tags usadas do Json
        final String OWM_LAT = "latitude";
        final String OWM_LONG = "longitude";

        //gera um array com cada elemento da lista que foi requisitada na query
        JSONArray arrayPos = new JSONArray(posJsonStr);

        //Array das strings que serao retornadas
        String[] resultStrs = new String[arrayPos.length()];
        for(int i = 0; i < arrayPos.length(); i++) {

            JSONObject posMomento = arrayPos.getJSONObject(i);  //pega o dado da i-esima posicao do array

            double latitude = posMomento.getDouble(OWM_LAT);  //Pega as informacoes que quer do json
            double longitude= posMomento.getDouble(OWM_LONG);

            resultStrs[i] = latitude + " " + longitude;  //Monta a string para a lista
        }

        return resultStrs;
    }


    //doInBackground é a funcao que efetivamente acontece em segundo plano. Aqui é feita a parte de rede. Se fosse feito dentra da thread principal ia trancar toda interface.
    //majoritariamente codigo boilerplate chato de conexao web.
    @Override
    protected String[] doInBackground(String... params){
        // These two need to be declared outside the try/catch
        // so that they can be closed in the finally block.
        HttpURLConnection urlConnection = null;
        BufferedReader reader = null;

        // Will contain the raw JSON response as a string.
        String stringPosJSon = null;

        try {
            Uri.Builder construtor = new Uri.Builder();
            //TODO: adicionar um jeito de mudar esse ip durante o tempo de execucao ou encontrar um outro jeito de nao ter que recompilar sempre que meu pc trocar de ip
            construtor.scheme("http").authority("192.168.0.103").appendPath("teste").appendPath("index.php");  //gera a url

            //TODO: TIRAR ESSA GAMBIARRA HORRENDA DAQUI PLMDDS
            String teste = construtor.toString()+"?ini="+params[0]+"&fim="+params[1]+"&id="+params[2];
            Log.d("TRETA","teste gera= "+teste);

            /*construtor.appendQueryParameter("ini",params[0]);
            construtor.appendQueryParameter("fim",params[1]);  //adiciona os parametros
            construtor.appendQueryParameter("id",params[2]);*/

            //Log.d("TRETA", "Formou URL " + construtor.toString());
            URL url = new URL(teste);

            // Create the request to OpenWeatherMap, and open the connection
            urlConnection = (HttpURLConnection) url.openConnection();
            urlConnection.setRequestMethod("GET");
            urlConnection.connect();

            // Read the input stream into a String
            InputStream inputStream = urlConnection.getInputStream();
            StringBuffer buffer = new StringBuffer();
            if (inputStream == null) {
                // Nothing to do.
                stringPosJSon = null;
            }
            reader = new BufferedReader(new InputStreamReader(inputStream));

            String line;
            while ((line = reader.readLine()) != null) {
                // Since it's JSON, adding a newline isn't necessary (it won't affect parsing)
                // But it does make debugging a *lot* easier if you print out the completed
                // buffer for debugging.
                buffer.append(line + "\n");
            }

            if (buffer.length() == 0) {
                // Stream was empty.  No point in parsing.
                stringPosJSon = null;
            }
            stringPosJSon = buffer.toString();

        } catch (IOException e) {
            Log.e("PlaceholderFragment", "Error ", e);
            // If the code didn't successfully get the weather data, there's no point in attempting
            // to parse it.
            stringPosJSon = null;
        } finally{
            if (urlConnection != null) {
                urlConnection.disconnect();
            }
            if (reader != null) {
                try {
                    reader.close();
                } catch (final IOException e) {
                    Log.e("PlaceholderFragment", "Error closing stream", e);
                }
            }
        }
        try {
            return getPosFromJSON(stringPosJSon);
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    //Depois que roda tudo, atualiza a listView com as strings que vieram do servidor.
    @Override
    protected void onPostExecute(String[] strings) {
        ListView lista = (ListView) mRootView.findViewById(R.id.listView);
        ArrayAdapter<String> adapter= new ArrayAdapter<String>(mContext,R.layout.layout_item_da_lista,R.id.textView_item_da_lista,strings);
        lista.setAdapter(adapter);
    }
}
