#include "Processo.h"

Processo::Processo(int processoId, int criacao, int dur, int priori) {
   this->id = processoId;
   this->dataDeCriacao = criacao;
   this->duracao = dur;
   this->prioridade = priori;
}

Processo::~Processo() {}

bool Processo::operator< (const Processo &other) const {
        return this->dataDeCriacao < other.dataDeCriacao;
}

std::ostream& operator<<(std::ostream& os, const Processo& processo) {
   os << "Processo " << processo.id << ": " << processo.dataDeCriacao << " | ";
   os << processo.duracao << " | " << processo.prioridade << std::endl;

   return os;
}

