package com.example.douglas.prototiporfid;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

/**
 * Created by douglas on 12/10/14.
 * Fragmento que só contem uma listView. Ele cria a lista e dispara a Thread que vai pegar os dados do servidor
 */
public class FragmentoListaPos extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_lista_pos, container, false);

        String[] argumentos = new String[3];//= new ArrayList<String>();

        argumentos[0]= getActivity().getIntent().getStringExtra("INICIO");
        argumentos[1]= getActivity().getIntent().getStringExtra("FIM");
        argumentos[2]=getActivity().getIntent().getStringExtra("ID");
        //TODO: efetivamente usar os dados em vez de só jogar eles em uma lista
        //TODO: se quiser tambem testar por dois textviews por item da lista para aprender como se faz isso pode ser interessante tambem.
        new ThreadPegaDados(getActivity(),rootView).execute(argumentos);
        return rootView;
    }
}
