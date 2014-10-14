package com.example.douglas.prototiporfid;

import android.app.Fragment;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.NumberPicker;

/*
    Fragment do seletor. Nada de muito emocionante aqui. So alguns datePickers para escolher a data de inicio e fim.
    Tem também um numpicker para escolher qual id quer ser queryada e um botao para enviar o request.
*/
public class FragmentoSeletor extends Fragment {

    public FragmentoSeletor() {
    }

    //Funcaozinha que formata a data do datepicker para o formato que o api que roda no servidor precisa
    private String formata(DatePicker data,boolean inicio){
        if(inicio)
            return data.getYear()+"-"+data.getMonth()+"-"+data.getDayOfMonth()+"+00:00:00";
        else
            return data.getYear()+"-"+data.getMonth()+"-"+data.getDayOfMonth()+"+23:59:59";
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_atividade_principal, container, false);

        //Pega algumas referencias e limita o numberPicker. Nada demais
        Button botao = (Button)rootView.findViewById(R.id.buttonVai);
        final DatePicker dataInicio = (DatePicker) rootView.findViewById(R.id.datePickerInicio);
        final DatePicker dataFim = (DatePicker) rootView.findViewById(R.id.datePickerFim);
        final NumberPicker seletorID = (NumberPicker) rootView.findViewById(R.id.numberPickerID);
        seletorID.setMinValue(1);
        seletorID.setMaxValue(10);
        //TODO: botar aqueles negocios legais de escolher data em um menu de tela inteira que fica em cima das coisas em vez dessa coisa horrenda que ocupa um espaco enorme que estao sendo usadas agora



        //TODO: tratar o caso de por duas datas para as quais nao tem nenhuma entrada na tabela.
        botao.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //Cria o intent de troca de atividade e adiciona as informacoes que serao usadas para disparar a thread de query
                Intent vaiPraLista = new Intent(getActivity(),AtividadeLista.class);
                vaiPraLista.putExtra("INICIO",formata(dataInicio,true));
                vaiPraLista.putExtra("FIM",formata(dataFim, false));
                vaiPraLista.putExtra("ID",String.valueOf(seletorID.getValue()));
                startActivity(vaiPraLista);
                Log.d("TRETA",formata(dataInicio,true));
            }
        });



        return rootView;
    }
}